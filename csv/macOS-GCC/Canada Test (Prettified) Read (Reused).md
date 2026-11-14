
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1166.06 | 1.09183 | 7461ms | 5212421 | 80 | 1.73315e+11 | 4.26302e+06 | 4.78833 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1119.32 | 0.873404 | 7908.6ms | 5212421 | 40 | 6.0181e+10 | 4.44104e+06 | 7.70958 | -(Loss) | false |
