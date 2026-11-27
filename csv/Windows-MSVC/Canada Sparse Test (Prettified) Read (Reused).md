
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11258.7 | 0.12318 | 5628.88ms | 5212421 | 160 | 4.73264e+07 | 441519 | 0.222738 | 0.269819 | 1(Win) | true |
| simdjson (ondemand) | 8472.05 | 0.200714 | 7436.67ms | 5212421 | 80 | 1.10955e+08 | 586748 | 0.0272764 | 0.358645 | 2(Loss) | true |
