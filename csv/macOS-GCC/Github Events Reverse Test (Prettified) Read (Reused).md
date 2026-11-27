
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1211.66 | 0.0659801 | 5937.31ms | 65103 | 2560 | 2.92623e+06 | 51241.4 | 0.211996 | 1(Win) | true |
| simdjson (ondemand) | 600.065 | 0.146397 | 5871.86ms | 65103 | 160 | 3.67102e+06 | 103467 | 0.0324635 | 2(Loss) | true |
