
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2357.87 | 0.0530087 | 565.776ms | 11579 | 40 | 246.523 | 4683.3 | 0.141839 | 1.04379 | 1(Win) | true |
| Jsonifier | 2152.4 | 0.0478407 | 601.476ms | 11579 | 30 | 180.723 | 5130.37 | 0.0455015 | 1.14434 | 2(Loss) | true |
| simdjson (ondemand) | 2007.87 | 0.138842 | 633.356ms | 11579 | 30 | 1749.2 | 5499.67 | 0.0139422 | 1.22726 | 3(Loss) | true |
| Glaze | 1881.83 | 0.0807217 | 666.81ms | 11579 | 30 | 673.103 | 5868 | 0.0926784 | 1.30953 | 4(Loss) | true |
