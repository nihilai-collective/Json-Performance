
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2509.74 | 0.319596 | 479.7ms | 9578 | 640 | 86591.4 | 3639.54 | 0.934027 | 0.979105 | 1(Win) | true |
| Jsonifier (two-stage) | 2419.49 | 0.122169 | 517.732ms | 9578 | 4890 | 104024 | 3775.3 | 0.248543 | 1.01607 | 2(Loss) | true |
| Glaze | 1945.12 | 0.0493368 | 605.496ms | 9578 | 30 | 161.034 | 4696 | 0.256298 | 1.26614 | 3(Loss) | true |
| simdjson (ondemand) | 1579.67 | 0.0706048 | 710.405ms | 9578 | 30 | 500.041 | 5782.4 | 0.00576429 | 1.55995 | 4(Loss) | true |
