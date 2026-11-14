
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1945.54 | 0.0494959 | 979.814ms | 4857 | 4890 | 6790.49 | 2380.82 | 0.0365399 | 2.68949 | 11.2771 | 2.09656 | 0.00223791 | 3.75988e-05 | 3.49463e-06 | 1(Win) | true |
| simdjson (ondemand) | 1733.3 | 0.0630416 | 1003.33ms | 4857 | 1280 | 3632.89 | 2672.35 | 0.0961571 | 3.01546 | 12.0496 | 2.063 | 0.00151376 | 2.7988e-05 | 1.76935e-06 | 2(Loss) | true |
