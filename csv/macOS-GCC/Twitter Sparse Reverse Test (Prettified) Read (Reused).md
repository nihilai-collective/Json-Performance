
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3724.21 | 0.0803597 | 9409.81ms | 360584 | 4890 | 2.69234e+07 | 92336.3 | 0.24053 | 1(Win) | true |
| simdjson (ondemand) | 3086.85 | 0.141431 | 5883.84ms | 360584 | 640 | 1.58873e+07 | 111402 | 0.0582018 | 2(Loss) | true |
