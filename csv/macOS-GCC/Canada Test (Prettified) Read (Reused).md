
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1427.65 | 0.783621 | 6090.94ms | 5212421 | 30 | 2.23341e+10 | 3.48191e+06 | 1.89106 | 1(Win) | true |
| simdjson (ondemand) | 1350.41 | 0.275935 | 6415.16ms | 5212421 | 80 | 8.25373e+09 | 3.68107e+06 | 0.148961 | 2(Loss) | true |
