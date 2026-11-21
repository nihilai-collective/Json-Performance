
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 3428.93 | 0.703204 | 91.1158ms | 2889 | 640 | 20432.5 | 803.506 | 0.581689 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3408.7 | 0.664784 | 107.548ms | 2889 | 80 | 2309.77 | 808.275 | 1.6954 | 1(Tie) | true |
| Jsonifier (two-stage) | 3179.07 | 0.975083 | 84.7359ms | 2889 | 160 | 11426.1 | 866.656 | 0.595601 | 3(Loss) | true |
| Glaze | 2075.57 | 0.385108 | 142.625ms | 2889 | 1280 | 33450 | 1327.42 | 1.19995 | 4(Loss) | true |
