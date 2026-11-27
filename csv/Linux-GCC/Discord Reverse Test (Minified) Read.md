
----
### Discord Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 702.132 | 0.142923 | 8412.27ms | 56369 | 80 | 957936 | 76563.5 | 0.0487905 | 7.19967 | 34.0652 | 7.07589 | 0.0110752 | 1.64097e-05 | 8.20486e-06 | 1(Win) | true |
| simdjson (ondemand) | 194.64 | 0.125867 | 7257.5ms | 56369 | 640 | 7.73435e+07 | 276190 | 0.0489397 | 26.2383 | 132.888 | 28.2674 | 0.0365067 | 0.000293324 | 0.000205842 | 2(Loss) | true |
