
----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6975.44 | 0.125958 | 778.478ms | 4630 | 4890 | 3108.7 | 633.009 | 0.1018 | 0.784614 | 3.65594 | 0.505184 | 0.000433025 | 1.70489e-05 | 5.47686e-06 | 1(Win) | true |
| simdjson (ondemand) | 6598.44 | 0.0730862 | 781.824ms | 4630 | 160 | 38.2711 | 669.175 | 0.0766455 | 0.828588 | 4.10583 | 0.493089 | 0.000431965 | 2.69978e-06 | 0 | 2(Loss) | true |
