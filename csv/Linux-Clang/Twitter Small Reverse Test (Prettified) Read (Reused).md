
----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1137.57 | 0.144145 | 1046.48ms | 3770 | 40 | 830.203 | 3160.55 | 0.0363728 | 4.58941 | 19.0936 | 3.49788 | 0.00192971 | 4.64191e-05 | 1.98939e-05 | 1(Win) | true |
| simdjson (ondemand) | 467.395 | 0.0328326 | 1503.08ms | 3770 | 4890 | 31191.4 | 7692.32 | 0.224449 | 10.921 | 49.3541 | 8.41884 | 0.012025 | 6.44958e-05 | 2.52776e-05 | 2(Loss) | true |
