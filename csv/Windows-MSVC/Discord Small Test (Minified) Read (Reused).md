
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1170.09 | 0.102459 | 444.207ms | 4857 | 4890 | 80445.7 | 3958.65 | 0.286868 | 2.58479 | 1(Win) | true |
| simdjson (ondemand) | 1064.01 | 0.263716 | 484.659ms | 4857 | 30 | 3954.02 | 4353.33 | 0.0765111 | 2.84381 | 2(Loss) | true |
