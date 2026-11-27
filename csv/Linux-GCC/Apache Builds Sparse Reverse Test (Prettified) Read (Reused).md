
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3028.33 | 0.0241732 | 5154.45ms | 124597 | 2560 | 230312 | 39237.8 | 0.0197903 | 1.68228 | 8.40273 | 1.529 | 0.00406548 | 4.85628e-06 | 2.26668e-06 | 1(Win) | true |
| simdjson (ondemand) | 2453.92 | 0.0223028 | 6048.97ms | 124597 | 2560 | 298576 | 48422.5 | 0.00518978 | 2.07634 | 8.72503 | 1.54098 | 0.00646117 | 8.83473e-06 | 5.64319e-06 | 2(Loss) | true |
