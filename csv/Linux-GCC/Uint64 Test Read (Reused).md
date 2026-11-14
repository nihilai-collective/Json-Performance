
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1394.01 | 0.0538017 | 976.302ms | 3873 | 1280 | 2601.15 | 2649.61 | 0.00869898 | 3.75076 | 17.6558 | 1.89801 | 0.000553511 | 7.50387e-05 | 2.09786e-05 | 1(Win) | true |
| simdjson (ondemand) | 755.37 | 0.0470156 | 1201.31ms | 3873 | 1280 | 6765.03 | 4889.76 | 0.00968316 | 6.87023 | 31.3016 | 3.56468 | 0.00745707 | 3.67125e-05 | 1.41202e-06 | 2(Loss) | true |
