
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5637.74 | 0.169816 | 778.136ms | 2889 | 40 | 27.5487 | 488.7 | 0.00682128 | 0.968562 | 3.75389 | 0.514365 | 0.000354794 | 1.7307e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 5577.54 | 0.298466 | 776.303ms | 2889 | 40 | 86.9481 | 493.975 | 0.30777 | 0.980036 | 3.78262 | 0.433714 | 0.000536518 | 3.46141e-05 | 0 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5564.53 | 0.244981 | 779.453ms | 2889 | 4890 | 7194.71 | 495.13 | 0.0644553 | 0.984639 | 3.75389 | 0.514365 | 0.000355272 | 5.18857e-05 | 1.50065e-05 | 2(Tie) | true |
| Glaze | 3109.93 | 0.103415 | 817.27ms | 2889 | 2560 | 2148.83 | 885.925 | 0.0903517 | 1.69963 | 6.80547 | 1.23364 | 0.000357633 | 2.78535e-05 | 3.51549e-06 | 4(Loss) | true |
