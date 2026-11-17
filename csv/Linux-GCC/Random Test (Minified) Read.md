
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22408.9 | 0.0230615 | 1969.81ms | 461466 | 40 | 820.487 | 19639 | 0.0808536 | 0.110326 | 1(Win) | true |
| simdjson (stage-1) | 15832.6 | 0.19909 | 2805.43ms | 461466 | 320 | 979998 | 27796.4 | 0.0120534 | 0.156221 | 2(Loss) | true |
