
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1766.39 | 0.0345847 | 1364.5ms | 11812 | 4890 | 23787.6 | 6377.3 | 0.219734 | 2.9067 | 13.7036 | 2.57831 | 0.00762167 | 1.78322e-05 | 4.25895e-06 | 1(Win) | true |
| simdjson (ondemand) | 1614.25 | 0.0255241 | 1428.04ms | 11812 | 4890 | 15513.6 | 6978.34 | 0.0906442 | 3.1737 | 14.3788 | 2.37843 | 0.00755833 | 2.37012e-05 | 8.36209e-06 | 2(Loss) | true |
