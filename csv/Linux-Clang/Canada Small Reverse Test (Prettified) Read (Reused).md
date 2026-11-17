
----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1899.13 | 0.0249313 | 1413.67ms | 11579 | 4890 | 10276.2 | 5814.56 | 0.113222 | 2.69007 | 13.5361 | 2.2774 | 0.000972266 | 1.32812e-05 | 1.23628e-06 | 1(Win) | true |
| Jsonifier (generic) | 1893.68 | 0.118143 | 1409.91ms | 11579 | 160 | 7593.91 | 5831.27 | 0.127278 | 2.7218 | 13.3912 | 2.44512 | 0.00106389 | 1.8892e-05 | 3.77839e-06 | 2(Loss) | true |
