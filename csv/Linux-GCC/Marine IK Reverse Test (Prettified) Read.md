
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2592.82 | 0.168799 | 8487.09ms | 7351818 | 30 | 6.25041e+08 | 2.7041e+06 | 0.734596 | 0.954858 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2588.1 | 0.135928 | 8430.89ms | 7351818 | 160 | 2.16952e+09 | 2.70903e+06 | 0.679266 | 0.956596 | 1(Tie) | true |
| simdjson (reflection) | 2306.65 | 0.0777227 | 9350.14ms | 7351818 | 160 | 8.92982e+08 | 3.03958e+06 | 0.698654 | 1.07332 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1951.28 | 0.251992 | 5342.08ms | 7351818 | 40 | 3.27932e+09 | 3.59314e+06 | 0.522367 | 1.26879 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1939.78 | 0.17853 | 5488.13ms | 7351818 | 30 | 1.24919e+09 | 3.61445e+06 | 0.34649 | 1.27632 | 4(Tie) | true |
