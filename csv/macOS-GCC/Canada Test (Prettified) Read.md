
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1164.88 | 1.01206 | 6822.36ms | 5373214 | 80 | 1.58565e+11 | 4.39898e+06 | 0.839251 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1098.26 | 1.07802 | 6851.98ms | 5373214 | 40 | 1.01197e+11 | 4.66582e+06 | 0.617035 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1086.59 | 0.659052 | 6650ms | 5373214 | 80 | 7.72806e+10 | 4.71596e+06 | 0.820113 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1012.91 | 1.27826 | 7399.96ms | 5373214 | 30 | 1.25454e+11 | 5.059e+06 | 0.91141 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1012.65 | 1.17407 | 7399.11ms | 5373214 | 40 | 1.41188e+11 | 5.06029e+06 | 1.65985 | 4(Tie) | true |
