
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2212.97 | 0.277435 | 8085.48ms | 676745 | 160 | 1.04747e+08 | 291641 | 0.0646781 | 1.37332 | 1(Win) | true |
| simdjson (ondemand) | 1700.2 | 0.518284 | 5118.37ms | 676745 | 320 | 1.23861e+09 | 379598 | 0.194993 | 1.78751 | 2(Loss) | true |
