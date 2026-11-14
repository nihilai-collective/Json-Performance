
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2446.81 | 0.238837 | 842.547ms | 2889 | 40 | 289.307 | 1126.03 | 0.121962 | 2.17919 | 6.76186 | 1.14573 | 0.00139322 | 0.000242298 | 0 | 1(Win) | true |
| Glaze | 2431.88 | 0.148482 | 839.861ms | 2889 | 4890 | 13837.8 | 1132.94 | 0.377295 | 2.15583 | 8.73659 | 1.49533 | 0.000357679 | 6.54057e-05 | 1.98199e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2174.55 | 0.260851 | 855.798ms | 2889 | 2560 | 27962.8 | 1267.01 | 0.174156 | 2.41682 | 8.1163 | 1.27137 | 0.00069823 | 4.1645e-05 | 5.13802e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1028.61 | 0.250077 | 995.838ms | 2889 | 30 | 1346.05 | 2678.53 | 0.0298582 | 4.98967 | 16.9013 | 2.86743 | 0.000403831 | 0.000196146 | 0.00011538 | 4(Loss) | true |
