
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19937.4 | 0.0428947 | 263.104ms | 56369 | 40 | 53.5071 | 2696.32 | 0.0330806 | 0.122955 | 1(Win) | true |
| simdjson (stage-1) | 16539.5 | 0.0544994 | 327.335ms | 56369 | 30 | 94.1333 | 3250.27 | 0.0194818 | 0.148321 | 2(Loss) | true |
