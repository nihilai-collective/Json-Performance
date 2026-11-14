
----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2985.04 | 0.0201411 | 2822.43ms | 56369 | 4890 | 64336.2 | 18009 | 0.0439876 | 1.71467 | 8.30045 | 1.42202 | 0.00273841 | 5.84811e-06 | 1.16454e-06 | 1(Win) | true |
| simdjson (ondemand) | 2422.54 | 0.0508196 | 3238.49ms | 56369 | 1280 | 162784 | 22190.6 | 0.0310792 | 2.12285 | 8.82655 | 1.35461 | 0.0065577 | 4.89243e-06 | 1.42754e-06 | 2(Loss) | true |
