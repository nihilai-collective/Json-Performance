
----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14170.1 | 3.76741 | 15.9232ms | 1996 | 4890 | 125248 | 134.335 | 1.07912 | 1(Win) | true |
| simdjson (reflection) | 12071.9 | 3.31853 | 18.3539ms | 1996 | 4890 | 133897 | 157.683 | 0.389491 | 2(Loss) | true |
| Glaze | 3733.87 | 1.42105 | 53.0662ms | 1996 | 4890 | 256643 | 509.801 | 0.572347 | 3(Loss) | true |
