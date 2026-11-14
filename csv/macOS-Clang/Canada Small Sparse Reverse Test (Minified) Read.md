
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3554.97 | 0.0808557 | 128.401ms | 4630 | 320 | 322.748 | 1242.07 | 0.0110715 | 1(Win) | true |
| simdjson (ondemand) | 3406.44 | 0.0706581 | 135.304ms | 4630 | 320 | 268.432 | 1296.22 | 0.0713102 | 2(Loss) | true |
