
----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 1548.25 | 0.0647105 | 1029.17ms | 4918 | 4890 | 18791.1 | 3029.33 | 0.00329293 | 3.36215 | 11.2717 | 1.32351 | 0.000532579 | 4.9108e-05 | 2.17057e-05 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1449.15 | 0.125056 | 1029.49ms | 4604 | 4890 | 70204.4 | 3029.86 | 0.185154 | 3.58835 | 9.4268 | 0.5404 | 0.000316787 | 6.4228e-05 | 3.04261e-05 | 1(Tie) | true |
| Glaze | 1242.74 | 0.0555026 | 1079.39ms | 4604 | 4890 | 18803.9 | 3533.1 | 0.0614508 | 4.18177 | 12.2024 | 0.968289 | 0.000778375 | 3.23805e-05 | 1.27923e-05 | 3(Loss) | true |
