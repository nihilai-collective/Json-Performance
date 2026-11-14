
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 668.657 | 0.862867 | 8074.8ms | 1834197 | 30 | 1.5286e+10 | 2.61603e+06 | 1.66341 | 1(Win) | true |
| Jsonifier (two-stage) | 534.547 | 0.160842 | 10188.7ms | 1834197 | 40 | 1.1081e+09 | 3.27235e+06 | 0.365887 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 455.772 | 0.611833 | 5443.49ms | 1834197 | 80 | 4.41116e+10 | 3.83794e+06 | 0.855969 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 445.579 | 1.06089 | 6062.51ms | 1834197 | 30 | 5.20361e+10 | 3.92573e+06 | 3.83331 | 3(Tie) | true |
| simdjson (ondemand) | 416.788 | 0.185791 | 6343.55ms | 1834197 | 80 | 4.86407e+09 | 4.19692e+06 | 0.435898 | 5(Loss) | true |
