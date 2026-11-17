
----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2843.19 | 0.0698569 | 805.586ms | 2632 | 2560 | 973.686 | 882.837 | 0.00805352 | 1.88934 | 8.40008 | 1.52432 | 0.00114071 | 6.53021e-05 | 1.70676e-05 | 1(Win) | true |
| simdjson (ondemand) | 2405.02 | 0.0224902 | 845.235ms | 2632 | 4890 | 269.42 | 1043.68 | 0.451947 | 2.22366 | 9.08663 | 1.46923 | 0.00129545 | 4.14903e-05 | 4.27334e-06 | 2(Loss) | true |
