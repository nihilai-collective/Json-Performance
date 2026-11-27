
----
### Canada Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11198.1 | 0.120117 | 5718.76ms | 5212421 | 160 | 4.54903e+07 | 443909 | 0.165996 | 0.450988 | 1.95455 | 0.198819 | 0.00219854 | 0.0393934 | 5.50008e-06 | 1(Win) | true |
| simdjson (ondemand) | 9546.31 | 0.0620958 | 6804.96ms | 5212421 | 320 | 3.34567e+07 | 520720 | 0.218791 | 0.532822 | 2.27766 | 0.202787 | 0.00216113 | 0.0394183 | 5.28425e-06 | 2(Loss) | true |
