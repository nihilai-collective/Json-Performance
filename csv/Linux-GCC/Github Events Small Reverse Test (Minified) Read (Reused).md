
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 989.428 | 0.108903 | 897.317ms | 1691 | 640 | 2016.41 | 1629.9 | 0.0571987 | 5.32452 | 19.3631 | 3.75931 | 0.00227029 | 8.22368e-05 | 1.66322e-05 | 1(Win) | true |
| simdjson (ondemand) | 782.125 | 0.0473008 | 939.308ms | 1691 | 4890 | 4651.36 | 2061.9 | 0.0926143 | 6.72017 | 26.3087 | 5.07688 | 0.00214101 | 9.72307e-05 | 2.33402e-05 | 2(Loss) | true |
