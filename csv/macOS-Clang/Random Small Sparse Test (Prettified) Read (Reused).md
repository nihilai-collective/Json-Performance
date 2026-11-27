
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2849.5 | 0.0898072 | 294.132ms | 8150 | 80 | 480.053 | 2727.65 | 0.0926563 | 1(Win) | true |
| simdjson (ondemand) | 2267.15 | 0.0516269 | 361.303ms | 8150 | 320 | 1002.44 | 3428.29 | 0.126955 | 2(Loss) | true |
