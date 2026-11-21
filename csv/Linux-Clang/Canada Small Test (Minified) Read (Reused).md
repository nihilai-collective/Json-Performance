
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1115.23 | 0.0611632 | 475.446ms | 4630 | 30 | 175.926 | 3959.27 | 0.0260923 | 2.20611 | 1(Win) | true |
| Jsonifier (two-stage) | 1006.62 | 0.180698 | 516.192ms | 4630 | 4890 | 307218 | 4386.48 | 0.261872 | 2.44456 | 2(Loss) | true |
| Glaze | 907.039 | 0.118814 | 573.024ms | 4630 | 40 | 1338.15 | 4868.05 | 0.178056 | 2.71565 | 3(Loss) | true |
| simdjson (ondemand) | 839.406 | 0.0506209 | 613.205ms | 4630 | 160 | 1134.48 | 5260.28 | 0.0041587 | 2.93515 | 4(Loss) | true |
