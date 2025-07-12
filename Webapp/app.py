import streamlit as st
import os
import subprocess
import pandas as pd
import joblib
import sys
from sklearn.preprocessing import LabelEncoder

# Add parent directory to import custom modules
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from dataset_gen import DatasetGenerator

# Define the required feature columns
REQUIRED_FEATURES = [
    'add', 'mul', 'load', 'store', 'call',
    'define', 'br i1', 'loops', 'basic_blocks', 'total_instructions'
]

# Streamlit UI setup
st.set_page_config(page_title="OptiML", page_icon="⚙️", layout="centered")

st.markdown("""
    <style>
    .main {
        background-color: #f5f7fa;
        padding: 2rem;
        border-radius: 10px;
    }
    .css-1aumxhk {
        background: linear-gradient(to right, #667eea, #764ba2);
        color: white;
        padding: 1rem;
        text-align: center;
        border-radius: 10px;
    }
    </style>
""", unsafe_allow_html=True)

st.markdown("<h1 class='css-1aumxhk'>OptiML - AI Compiler Optimizer 🚀</h1>", unsafe_allow_html=True)

# File uploader
uploaded_file = st.file_uploader("📁 Upload your C file", type=["c"])

if uploaded_file:
    # Save uploaded file to disk
    temp_c_path = os.path.abspath("temp.c")
    with open(temp_c_path, "wb") as f:
        f.write(uploaded_file.read())
    st.success("✅ File uploaded successfully!")

    # Feature extraction
    st.write("🔍 Extracting features...")
    try:
        generator = DatasetGenerator()
        raw_feats = generator.extract_features(temp_c_path)

        # Ensure all expected features are present
        feats = {feat: raw_feats.get(feat, 0) for feat in REQUIRED_FEATURES}
        input_df = pd.DataFrame([feats])

        st.success("✅ Features extracted!")
        st.write("📊 Extracted Features:")
        st.dataframe(input_df.T)

    except Exception as e:
        st.error(f"❌ Feature extraction failed: {e}")
        st.stop()

    # Load model and predict
    try:
        model_path = os.path.abspath("rf_model.pkl")
        model = joblib.load(model_path)
        

        # Load label encoder
        encoder_path = os.path.abspath("label_encoder.pkl")
        label_encoder = joblib.load(encoder_path)

        # Predict
        encoded_pred = model.predict(input_df)[0]
        original_flag = label_encoder.inverse_transform([encoded_pred])[0]

        st.success(f"🏁 Recommended Optimization Flag: `{original_flag}`")

    except Exception as e:
        st.error(f"❌ Model prediction failed: {e}")
