
----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6181.44 | 0.118874 | 757.24ms | 2821 | 2560 | 685.244 | 435.225 | 0.0502866 | 0.904811 | 3.60759 | 0.4743 | 0.000588222 | 3.62792e-05 | 1.50933e-05 | 1(Win) | true |
| simdjson (ondemand) | 5143.85 | 0.0600588 | 766.104ms | 2821 | 2560 | 252.594 | 523.016 | 0.135373 | 1.07754 | 4.14179 | 0.454449 | 0.000434797 | 2.43708e-05 | 5.26188e-06 | 2(Loss) | true |
