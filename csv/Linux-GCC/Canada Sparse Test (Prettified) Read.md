
----
### Canada Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11476.5 | 0.0767826 | 5615.85ms | 5212421 | 320 | 3.53947e+07 | 433143 | 0.138339 | 0.442065 | 1.96707 | 0.181297 | 0.00222042 | 0.0394179 | 3.16971e-06 | 1(Win) | true |
| simdjson (ondemand) | 9771.12 | 0.0382487 | 6585.06ms | 5212421 | 640 | 2.42328e+07 | 508739 | 0.0661882 | 0.524207 | 2.27766 | 0.202785 | 0.00214232 | 0.0393999 | 2.59986e-06 | 2(Loss) | true |
