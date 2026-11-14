
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6736.63 | 0.0619567 | 5245.69ms | 360584 | 4890 | 4.89118e+06 | 51046.2 | 0.0412748 | 0.450907 | 1(Win) | true |
| simdjson (ondemand) | 4872.66 | 0.132674 | 7224.49ms | 360584 | 640 | 5.61091e+06 | 70573.3 | 0.0683662 | 0.623501 | 2(Loss) | true |
