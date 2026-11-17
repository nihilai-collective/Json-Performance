
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 550.336 | 0.999251 | 6380.01ms | 2090234 | 30 | 3.93011e+10 | 3.62216e+06 | 0.650207 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 467.719 | 1.10314 | 7053.57ms | 2090234 | 40 | 8.84177e+10 | 4.26197e+06 | 6.0095 | -(Loss) | false |
