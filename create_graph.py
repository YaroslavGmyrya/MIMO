import sys
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

def main():
    if len(sys.argv) != 2:
        print("Добавьте файл с результатами теста")
        sys.exit(1)

    snr_db = []
    real_ber = []
    theory_ber = []

    input_file = sys.argv[1]

    with open(input_file, "r") as file:
        for line in file:
            words = line.strip().replace(":", "").split(" ")
            numbers = [float(word) for word in words if is_number(word)]

            if len(numbers) >= 3:
                snr_db.append(numbers[0])
                real_ber.append(numbers[1])
                theory_ber.append(numbers[2])

    data = pd.DataFrame({
        'SNR_DB': snr_db,
        'Real_BER': real_ber,
        'Theory_BER': theory_ber
    })

    plt.figure(figsize=(10, 6))
    
    sns.lineplot(data=data, x='SNR_DB', y='Real_BER', 
                 label='Real BER', marker='o', color='blue')
    
    sns.lineplot(data=data, x='SNR_DB', y='Theory_BER', 
                 label='Theoretical BER', marker='s', color='red')
    
    plt.title('Зависимость BER от SNR')
    plt.xlabel('SNR (dB)')
    plt.ylabel('Bit Error Rate (BER)')
    plt.yscale('log')
    plt.grid(True)
    plt.legend()
    
    plt.savefig('graph.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == '__main__':
    main()
