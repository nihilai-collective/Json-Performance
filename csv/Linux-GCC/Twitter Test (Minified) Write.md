
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17909 | 0.095302 | 3320.82ms | 475954 | 80 | 46674.6 | 25345 | 0.0112461 | 0.282653 | 1.00424 | 0.147998 | 0.000269774 | 0.00118386 | 8.50923e-06 | 1(Win) | true |
| simdjson (reflection) | 11034.5 | 0.0727805 | 4882.12ms | 475954 | 640 | 573636 | 41135.2 | 0.0563942 | 0.453336 | 1.30937 | 0.183999 | 0.000264728 | 0.000459163 | 1.37553e-05 | 2(Loss) | true |
| Glaze | 7721.32 | 0.091154 | 6693.58ms | 475954 | 4890 | 1.40413e+07 | 58785.9 | 0.384688 | 0.651846 | 2.22759 | 0.324916 | 0.000276325 | 0.0195694 | 2.0054e-05 | 3(Loss) | true |
