
----
### Apache Builds Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1296.42 | 0.128457 | 917.919ms | 2632 | 1280 | 7917.89 | 1936.16 | 0.448653 | 4.04789 | 16.0057 | 3.19567 | 0.00486174 | 0.00011042 | 5.22416e-05 | 1(Win) | true |
| simdjson (ondemand) | 713.136 | 0.100508 | 1072.62ms | 2632 | 80 | 1001.2 | 3519.76 | 0.0500995 | 7.30927 | 30.8518 | 5.89438 | 0.0136683 | 0.000128229 | 3.32447e-05 | 2(Loss) | true |
