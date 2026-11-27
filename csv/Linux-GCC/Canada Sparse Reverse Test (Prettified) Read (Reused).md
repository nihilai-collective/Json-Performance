
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8880.33 | 0.168933 | 7354.07ms | 5212421 | 30 | 2.68271e+07 | 559771 | 0.0463976 | 0.57387 | 2.53189 | 0.327117 | 0.00214075 | 0.059059 | 2.26382e-06 | 1(Win) | true |
| simdjson (ondemand) | 7711.09 | 0.0940845 | 8392.17ms | 5212421 | 320 | 1.17715e+08 | 644650 | 0.191851 | 0.656774 | 2.85496 | 0.331076 | 0.00215076 | 0.059134 | 1.22826e-05 | 2(Loss) | true |
