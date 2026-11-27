
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2601.31 | 0.0673014 | 966.138ms | 6701 | 1280 | 3499.07 | 2456.67 | 0.214736 | 2.01028 | 7.52455 | 1.40263 | 0.000746973 | 4.52358e-05 | 1.65554e-05 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2114.75 | 0.0800638 | 1022.32ms | 6701 | 1280 | 7492.78 | 3021.9 | 0.127073 | 2.42911 | 9.74168 | 1.53828 | 0.000933163 | 8.96555e-05 | 4.43031e-05 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2106.48 | 0.21429 | 1031.06ms | 6701 | 30 | 1267.91 | 3033.77 | 0.0373434 | 2.47847 | 9.7472 | 1.58021 | 0.000542208 | 0.00023877 | 0.000134308 | 2(Tie) | true |
| Glaze | 2025.81 | 0.113868 | 1039.84ms | 6701 | 80 | 1032.22 | 3154.57 | 0.0467356 | 2.57518 | 10.4326 | 2.11013 | 0.00108379 | 0.000119385 | 8.20773e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1756.86 | 0.0721968 | 1088.36ms | 6701 | 1280 | 8827.79 | 3637.5 | 0.26738 | 2.96758 | 10.8099 | 1.96359 | 0.00103576 | 4.08055e-05 | 1.10758e-05 | 5(Loss) | true |
