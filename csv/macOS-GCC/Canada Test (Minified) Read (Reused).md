
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 571.195 | 0.694935 | 6205.8ms | 2090234 | 40 | 2.35271e+10 | 3.48988e+06 | 1.53522 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 444.614 | 1.88474 | 6959.32ms | 2090234 | 80 | 5.71236e+11 | 4.48344e+06 | 6.0056 | -(Loss) | false |
