
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11488.6 | 0.0467432 | 3846.81ms | 461466 | 1280 | 410387 | 38306.6 | 0.0963556 | 0.264254 | 1(Win) | true |
| simdjson (stage-1) | 10372.5 | 0.0228387 | 4246.44ms | 461466 | 4890 | 459159 | 42428.2 | 0.0163886 | 0.292705 | 2(Loss) | true |
