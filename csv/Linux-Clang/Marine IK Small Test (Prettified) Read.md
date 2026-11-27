
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2893.42 | 0.168206 | 600.938ms | 18245 | 4890 | 500328 | 6013.58 | 0.240149 | 0.851449 | 1(Win) | true |
| Jsonifier | 2537.85 | 0.153788 | 690.345ms | 18245 | 2560 | 284604 | 6856.11 | 0.0535617 | 0.971769 | 2(Loss) | true |
| simdjson (ondemand) | 1925.4 | 0.0628739 | 947.759ms | 18245 | 30 | 968.516 | 9036.97 | 0.262946 | 1.28197 | 3(Loss) | true |
| Glaze | 1790.65 | 0.0682376 | 980.901ms | 18245 | 30 | 1318.97 | 9717 | 0.161834 | 1.37896 | 4(Loss) | true |
