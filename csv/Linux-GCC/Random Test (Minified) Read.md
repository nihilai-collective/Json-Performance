
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1389.12 | 0.114721 | 7383.57ms | 409725 | 640 | 6.6645e+07 | 281289 | 0.0507582 | 3.66498 | 17.0455 | 3.35093 | 0.00828847 | 0.0272856 | 4.22311e-05 | 1(Win) | true |
| simdjson (ondemand) | 1019 | 0.0988141 | 9971ms | 409725 | 640 | 9.18874e+07 | 383459 | 0.0660762 | 4.99044 | 19.9009 | 3.77083 | 0.0150898 | 0.0382456 | 0.000133844 | 2(Loss) | true |
