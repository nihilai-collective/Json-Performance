
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 829.981 | 0.143893 | 667.1ms | 4604 | 4890 | 283350 | 5290.14 | 0.0426432 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 640.009 | 0.151147 | 817.833ms | 4604 | 2560 | 275256 | 6860.4 | 0.131016 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 636.803 | 0.888905 | 882.249ms | 4604 | 30 | 112692 | 6894.93 | 0.372671 | 2(Tie) | true |
| Glaze | 530.485 | 0.373792 | 976.456ms | 4604 | 320 | 306291 | 8276.8 | 0.0580271 | 4(Loss) | true |
| simdjson (ondemand) | 445.965 | 0.0988562 | 1122.66ms | 4604 | 4890 | 463218 | 9845.42 | 0.178318 | 5(Loss) | true |
