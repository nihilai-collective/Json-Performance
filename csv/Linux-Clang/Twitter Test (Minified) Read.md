
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16160.1 | 0.0393792 | 3480.41ms | 466906 | 4890 | 575719 | 27554 | 0.101065 | 0.314982 | 1.73857 | 0.0858482 | 2.21013e-05 | 1.79005e-06 | 1.33761e-06 | 1(Win) | true |
| simdjson (stage-1) | 14041.4 | 0.0264913 | 3908.22ms | 466906 | 640 | 45167.3 | 31711.6 | 0.0943852 | 0.367015 | 1.74354 | 0.073925 | 5.7292e-06 | 2.73409e-06 | 2.23211e-06 | 2(Loss) | true |
