from flask import Flask, request, jsonify
from langchain_core.prompts import PromptTemplate
from langchain_ollama import OllamaLLM
import json
import os

app = Flask(__name__)

# Create Ollama model instance
llm = OllamaLLM(model="axon")

# Prompt template with previous questions and answers
template = """
Previous question: {previous_question}
Previous answer: {previous_answer}

Current question: {prompt}
"""

# Create PromptTemplate object
prompt_template = PromptTemplate(
    input_variables=["prompt", "previous_question", "previous_answer"],
    template=template
)

knowledge_base_file = 'knowledge_base.json'

# Store previous question and answer
previous_question = None
previous_answer = None

# Knowledge base management functions
def load_knowledge_base(file_path: str):
    if not os.path.exists(file_path):
        with open(file_path, 'w', encoding='utf-8') as file:
            json.dump({"questions": []}, file, ensure_ascii=False, indent=2)
        print("Created new knowledge base")
    with open(file_path, 'r', encoding='utf-8') as file:
        data = json.load(file)
    print("Loaded knowledge base:", data)
    return data

def save_knowledge_base(file_path: str, data: dict):
    with open(file_path, 'w', encoding='utf-8') as file:
        json.dump(data, file, ensure_ascii=False, indent=2)

def find_best_match(user_question: str, questions: list):
    user_question = user_question.lower().strip()
    normalized_questions = [q.lower().strip() for q in questions]
    from difflib import get_close_matches
    matches = get_close_matches(user_question, normalized_questions, n=1, cutoff=0.7)
    return matches[0] if matches else None

def get_answer_and_action_for_question(question: str, knowledge_base: dict):
    for q in knowledge_base["questions"]:
        if q["question"] == question:
            return q["answer"], q.get("action", None)
    return None, None

# Ollama communication function
def chat_with_ollama(user_prompt):
    global previous_question, previous_answer

    # If no previous question/answer, set to "none"
    if not previous_question or not previous_answer:
        previous_question = "none"
        previous_answer = "none"

    # Generate prompt
    prompt = prompt_template.format(
        prompt=user_prompt,
        previous_question=previous_question,
        previous_answer=previous_answer
    )
    
    # Query the LLM
    response = llm.invoke(prompt)
    
    # Update previous question and answer
    previous_question = user_prompt
    previous_answer = response.strip() if response else "Bot: There was a problem processing the response."
    
    return previous_answer

# Process user input with knowledge base
def process_user_input(user_input):
    knowledge_base = load_knowledge_base(knowledge_base_file)
    best_match = find_best_match(user_input, [q["question"] for q in knowledge_base["questions"]])

    if best_match:
        answer, action = get_answer_and_action_for_question(best_match, knowledge_base)
        return {"answer": answer, "action": action, "new_entry": False}
    else:
        response = chat_with_ollama(user_input)
        if response:
            # When generating new response, action is None - can extend LLM logic if we want dynamic action generation
            return {"answer": response, "action": None, "new_entry": True}
        else:
            return {"answer": "Bot: There was a problem processing the response.", "action": None, "new_entry": False}

@app.route('/send', methods=['POST'])
def send_message():
    data = request.json
    message = data.get('message')
    
    if message:
        result = process_user_input(message)
        return jsonify(result)
    
    return jsonify({'status': 'No message received'}), 400

@app.route('/save', methods=['POST'])
def save_message():
    data = request.json
    question = data.get('question')
    answer = data.get('answer')
    action = data.get('action', None)
    
    if question and answer:
        knowledge_base = load_knowledge_base(knowledge_base_file)
        knowledge_base["questions"].append({"question": question, "answer": answer, "action": action})
        save_knowledge_base(knowledge_base_file, knowledge_base)
        return jsonify({'status': 'saved'})
    
    return jsonify({'status': 'failed'}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
