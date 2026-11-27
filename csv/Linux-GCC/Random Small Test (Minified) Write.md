
----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12636 | 0.0939607 | 755.789ms | 5094 | 1280 | 167.034 | 384.459 | 0.292977 | 0.45013 | 1.71928 | 0.228897 | 0.000196309 | 3.88018e-05 | 9.50874e-06 | 1(Win) | true |
| simdjson (reflection) | 8379.22 | 0.177434 | 776.412ms | 5094 | 4890 | 5174.82 | 579.77 | 0.0849011 | 0.663299 | 2.40616 | 0.34413 | 0.000196631 | 6.87685e-05 | 3.31197e-05 | 2(Loss) | true |
| Glaze | 4276.52 | 0.0991602 | 835.989ms | 5094 | 4890 | 6204.69 | 1135.97 | 0.0822399 | 1.24974 | 5.14978 | 0.826659 | 0.000197313 | 7.46698e-05 | 2.10762e-05 | 3(Loss) | true |
