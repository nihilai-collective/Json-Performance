
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1778.88 | 0.0745634 | 8999.27ms | 5373214 | 80 | 3.69075e+08 | 2.88062e+06 | 0.105088 | 1.39176 | 1(Win) | true |
| Jsonifier | 1755.08 | 0.0951693 | 9071.32ms | 5373214 | 40 | 3.08837e+08 | 2.9197e+06 | 0.234672 | 1.41063 | 2(Loss) | true |
| simdjson (ondemand) | 1708.34 | 0.0329106 | 9311.18ms | 5373214 | 160 | 1.55924e+08 | 2.99958e+06 | 0.128379 | 1.44923 | 3(Loss) | true |
| Glaze | 1605.72 | 0.101452 | 9901.98ms | 5373214 | 40 | 4.19291e+08 | 3.19128e+06 | 0.0377464 | 1.54186 | 4(Loss) | true |
