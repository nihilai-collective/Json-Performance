
----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10007.7 | 1.76768 | 47.8318ms | 4857 | 4890 | 327327 | 462.842 | 0.924928 | 1(Win) | true |
| simdjson (reflection) | 6936.2 | 1.56009 | 66.335ms | 4857 | 2560 | 277864 | 667.8 | 1.82299 | 2(Loss) | true |
| Glaze | 2598.74 | 1.05417 | 197.353ms | 4857 | 640 | 225950 | 1782.4 | 0.768883 | 3(Loss) | true |
