
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) DID NOT CONVERGE | 568.22 | 0.09257 | 6444.03ms | 2090234 | 30 | 3.16388e+08 | 3.50816e+06 | 6.52572 | -(Win) | false |
| Jsonifier (generic) | 530.299 | 1.30755 | 5911.22ms | 2090234 | 40 | 9.66324e+10 | 3.75902e+06 | 2.46864 | 2(Loss) | true |
