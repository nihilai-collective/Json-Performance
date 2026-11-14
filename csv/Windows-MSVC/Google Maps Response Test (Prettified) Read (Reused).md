
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1435.81 | 0.0454673 | 1794.03ms | 25388 | 4890 | 287456 | 16862.9 | 0.0727477 | 2.11379 | 1(Win) | true |
| simdjson (ondemand) | 1300.02 | 0.082932 | 1963.59ms | 25388 | 4890 | 1.16656e+06 | 18624.2 | 0.345551 | 2.33505 | 2(Loss) | true |
