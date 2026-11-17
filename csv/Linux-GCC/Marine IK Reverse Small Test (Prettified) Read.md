
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2629.25 | 0.143392 | 652.144ms | 18245 | 2560 | 230522 | 6617.78 | 0.415689 | 0.937803 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 2317.53 | 0.0976302 | 763.529ms | 18245 | 4890 | 262732 | 7507.89 | 0.0890018 | 1.06462 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2314.03 | 0.244713 | 767.886ms | 18245 | 640 | 216693 | 7519.25 | 0.208838 | 1.06624 | 2(Tie) | true |
| simdjson (ondemand) | 1990.06 | 0.123743 | 876.213ms | 18245 | 30 | 3511.68 | 8743.33 | 0.210384 | 1.24012 | 4(Loss) | true |
| Glaze | 1919.13 | 0.0451924 | 916.723ms | 18245 | 40 | 671.538 | 9066.5 | 0.00845532 | 1.28628 | 5(Loss) | true |
