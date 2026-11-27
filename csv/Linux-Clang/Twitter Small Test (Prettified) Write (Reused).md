
----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12492 | 0.199988 | 35.4302ms | 4300 | 80 | 34.4804 | 328.275 | 0.0762137 | 0.182038 | 1(Win) | true |
| Glaze | 4675.41 | 0.224073 | 90.7826ms | 4300 | 40 | 154.503 | 877.1 | 0.236181 | 0.513924 | 2(Loss) | true |
